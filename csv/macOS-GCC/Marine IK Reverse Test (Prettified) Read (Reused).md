
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2116.59 | 0.228394 | 5876.82ms | 7351818 | 40 | 2.28953e+09 | 3.31251e+06 | 0.19848 | 1(Win) | true |
| Jsonifier (two-stage) | 1857.04 | 0.551845 | 6230.86ms | 7351818 | 30 | 1.30227e+10 | 3.77549e+06 | 1.30364 | 2(Loss) | true |
| simdjson (reflection) | 1810.34 | 0.243525 | 6587.04ms | 7351818 | 30 | 2.66856e+09 | 3.87289e+06 | 0.899614 | 3(Loss) | true |
| simdjson (ondemand) | 1610.55 | 0.255799 | 7236.93ms | 7351818 | 30 | 3.72014e+09 | 4.35331e+06 | 0.973467 | 4(Loss) | true |
| Glaze | 1567.39 | 0.265786 | 7370.37ms | 7351818 | 30 | 4.24052e+09 | 4.47318e+06 | 0.0796769 | 5(Loss) | true |
