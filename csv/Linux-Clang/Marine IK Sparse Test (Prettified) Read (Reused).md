
----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10038.9 | 0.109045 | 8993.95ms | 7351818 | 160 | 9.28006e+07 | 698410 | 0.00575649 | 0.505534 | 2.37647 | 0.241955 | 0.00104488 | 0.0423798 | 0.000183039 | 1(Win) | true |
| simdjson (ondemand) | 9814.47 | 0.0292216 | 9237.38ms | 7351818 | 320 | 1.39448e+07 | 714378 | 0.21071 | 0.52446 | 2.49475 | 0.256642 | 0.00095106 | 0.0424027 | 2.08966e-05 | 2(Loss) | true |
