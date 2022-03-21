import router from '@ohos.router';

var numbs = 0;
var code = 0;
var inputVal = 0;
var EVENT_CONFIRM = "EVENT_CONFIRM";
var EVENT_CANCEL = "EVENT_CANCEL";
var EVENT_INIT = "EVENT_INIT";
var EVENT_CONFIRM_CODE = "0";
var EVENT_CANCEL_CODE = "1";
var EVENT_INIT_CODE = "2";
export default {
    data: {
        pincode: router.getParams().pinCode,
        isShow:false,
        isTimes:3,
    },
    onInit() {
        code = router.getParams().pinCode;
        callNativeHandler(EVENT_INIT, EVENT_INIT_CODE);
    },
    onChange(e){ 
        inputVal = e.value; 
    }, 
    onConfirm() {
        numbs = numbs + 1;
        if(numbs <= 3){
            console.info('click confirm numbs < 3 ');
            if(code == inputVal){
                console.info('click confirm code == inputVal');
                callNativeHandler(EVENT_CONFIRM, EVENT_CONFIRM_CODE);
            }else{
                if(numbs == 3){
                    console.info('click confirm code != inputVal and numbs == 3');
                    callNativeHandler(EVENT_CANCEL, EVENT_CANCEL_CODE);
                }
                console.info('click confirm code != inputVal');
                this.isShow = true;
                this.isTimes = 3 - numbs;
            }
        }else{
            console.info('click confirm numbs > 3 ');
            callNativeHandler(EVENT_CANCEL, EVENT_CANCEL_CODE);
        }       
    },
    onCancel() {
        console.info('click cancel');
        callNativeHandler(EVENT_CANCEL, EVENT_CANCEL_CODE);
    }
}