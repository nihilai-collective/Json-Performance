
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 925.578 | 0.0555481 | 6556.51ms | 1834197 | 160 | 1.7633e+08 | 1.88988e+06 | 0.172718 | 5.46378 | 22.778 | 5.08164 | 0.0357114 | 0.0560481 | 0.002178 | 1(Win) | true |
| Jsonifier (two-stage) | 779.004 | 0.0597177 | 7641.49ms | 1834197 | 80 | 1.4385e+08 | 2.24547e+06 | 0.308985 | 6.46796 | 27.0056 | 5.57276 | 0.0453811 | 0.120249 | 0.00411046 | 2(Loss) | true |
| simdjson (reflection) | 749.102 | 0.117451 | 7859.34ms | 1834197 | 40 | 3.00873e+08 | 2.3351e+06 | 0.0586284 | 6.75192 | 29.2207 | 5.23318 | 0.0262045 | 0.111857 | 0.00550654 | 3(Loss) | true |
| Glaze | 714.293 | 0.11377 | 8299.63ms | 1834197 | 80 | 6.20987e+08 | 2.44889e+06 | 0.00271697 | 7.0624 | 29.3687 | 5.62402 | 0.0330404 | 0.0582665 | 0.00134959 | 4(Loss) | true |
| simdjson (ondemand) | 592.396 | 0.0742421 | 9894.28ms | 1834197 | 80 | 3.84467e+08 | 2.9528e+06 | 0.146314 | 8.55334 | 34.5296 | 6.46274 | 0.0315287 | 0.117938 | 0.02178 | 5(Loss) | true |
