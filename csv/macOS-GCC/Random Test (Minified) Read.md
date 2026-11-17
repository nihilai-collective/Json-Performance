
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 936.036 | 0.279062 | 6005.49ms | 461466 | 160 | 2.75433e+08 | 470162 | 0.586297 | 1(Win) | true |
| Jsonifier (two-stage) | 795.767 | 1.92791 | 7216.89ms | 461466 | 30 | 3.41037e+09 | 553037 | 2.28424 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 727.529 | 0.498455 | 8004.09ms | 461466 | 640 | 5.81849e+09 | 604908 | 3.36943 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 720.636 | 1.24599 | 7898.3ms | 461466 | 40 | 2.316e+09 | 610694 | 0.486879 | 3(Tie) | true |
| simdjson (ondemand) | 579.697 | 0.498918 | 9230.95ms | 461466 | 320 | 4.59078e+09 | 759170 | 2.64181 | 5(Loss) | true |
