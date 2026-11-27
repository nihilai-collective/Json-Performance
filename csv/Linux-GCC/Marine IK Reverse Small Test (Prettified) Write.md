
----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6974.52 | 0.10218 | 1062.88ms | 24893 | 4890 | 59152 | 3403.79 | 0.336516 | 0.747605 | 1.88061 | 0.0970153 | 4.47149e-05 | 2.39306e-05 | 1.26431e-05 | 1(Win) | true |
| Glaze | 3432.71 | 0.0800256 | 1410.17ms | 24579 | 4890 | 146023 | 6828.52 | 0.041441 | 1.51507 | 3.92176 | 0.474715 | 0.000199781 | 1.99432e-05 | 5.67429e-06 | 2(Loss) | true |
| simdjson (reflection) | 547.099 | 0.152849 | 5071.98ms | 24893 | 2560 | 1.12613e+07 | 43392.2 | 0.0640854 | 9.38049 | 35.6264 | 5.71968 | 0.00697063 | 0.000133195 | 7.89943e-05 | 3(Loss) | true |
