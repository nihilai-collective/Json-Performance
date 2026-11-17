
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 681.968 | 1.09639 | 8982.77ms | 1834197 | 80 | 6.32684e+10 | 2.56497e+06 | 0.45405 | 1(Win) | true |
| Jsonifier (two-stage) | 613.284 | 0.29339 | 10067.1ms | 1834197 | 80 | 5.60208e+09 | 2.85223e+06 | 0.693415 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 518.597 | 0.360946 | 5634.09ms | 1834197 | 30 | 4.44669e+09 | 3.373e+06 | 1.17409 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 514.7 | 0.401867 | 5861.66ms | 1834197 | 40 | 7.46117e+09 | 3.39853e+06 | 1.03985 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 514.5 | 0.947718 | 5670.37ms | 1834197 | 30 | 3.11459e+10 | 3.39986e+06 | 1.56076 | 3(Tie) | true |
