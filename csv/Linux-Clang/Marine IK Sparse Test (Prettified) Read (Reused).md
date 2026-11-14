
----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10211.3 | 0.123244 | 8861.3ms | 7351818 | 80 | 5.72856e+07 | 686615 | 0.0371106 | 0.497501 | 2.37647 | 0.241955 | 0.00107651 | 0.0423764 | 0.00025096 | 1(Win) | true |
| simdjson (ondemand) | 9581.8 | 0.158774 | 9424.47ms | 7351818 | 40 | 5.39901e+07 | 731724 | 0.0684549 | 0.533179 | 2.49474 | 0.25664 | 0.000979577 | 0.0424141 | 0.000230392 | 2(Loss) | true |
