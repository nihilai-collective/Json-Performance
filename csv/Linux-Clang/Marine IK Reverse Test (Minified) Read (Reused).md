
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 960.841 | 0.0437563 | 6403.76ms | 1834197 | 160 | 1.01529e+08 | 1.82052e+06 | 0.246577 | 2.57661 | 1(Win) | true |
| Jsonifier (two-stage) | 816.583 | 0.190785 | 7512.84ms | 1834197 | 30 | 5.01072e+08 | 2.14213e+06 | 0.594645 | 3.03186 | 2(Loss) | true |
| Glaze | 771.795 | 0.0501031 | 7879.8ms | 1834197 | 160 | 2.06318e+08 | 2.26644e+06 | 0.285249 | 3.20784 | 3(Loss) | true |
| simdjson (ondemand) | 624.584 | 0.217988 | 9290.26ms | 1834197 | 30 | 1.11814e+09 | 2.80063e+06 | 0.035513 | 3.96365 | 4(Loss) | true |
