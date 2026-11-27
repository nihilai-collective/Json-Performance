
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 883.445 | 0.0808189 | 6800.86ms | 1834197 | 160 | 4.09713e+08 | 1.98001e+06 | 0.284672 | 5.72197 | 23.9201 | 5.22004 | 0.0298412 | 0.0550519 | 0.000295841 | 1(Win) | true |
| Jsonifier (two-stage) | 808.459 | 0.101876 | 7423.97ms | 1834197 | 30 | 1.4576e+08 | 2.16366e+06 | 0.0499759 | 6.26948 | 28.6526 | 5.99382 | 0.0386984 | 0.119158 | 0.000149911 | 2(Loss) | true |
| Glaze | 761.767 | 0.107935 | 7865.17ms | 1834197 | 40 | 2.45715e+08 | 2.29628e+06 | 0.0833666 | 6.62538 | 28.9944 | 5.79293 | 0.0340193 | 0.0580723 | 8.5487e-05 | 3(Loss) | true |
| simdjson (ondemand) | 647.977 | 0.084022 | 9081.77ms | 1834197 | 160 | 8.23151e+08 | 2.69952e+06 | 0.0426104 | 7.81174 | 33.8345 | 5.52875 | 0.0363622 | 0.118529 | 0.000996761 | 4(Loss) | true |
