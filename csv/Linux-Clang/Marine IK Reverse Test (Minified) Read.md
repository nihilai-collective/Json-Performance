
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 830.256 | 1.06089 | 6631.17ms | 1834197 | 160 | 7.99335e+10 | 2.10685e+06 | 1.48802 | 2.98193 | 1(Win) | true |
| Jsonifier (two-stage) | 788.081 | 0.108375 | 6976.19ms | 1834197 | 30 | 1.73591e+08 | 2.2196e+06 | 0.226639 | 3.14152 | 2(Loss) | true |
| Glaze | 678.954 | 0.0617451 | 8040.95ms | 1834197 | 80 | 2.02444e+08 | 2.57635e+06 | 0.0865522 | 3.64646 | 3(Loss) | true |
| simdjson (ondemand) | 629.91 | 0.254963 | 8855.73ms | 1834197 | 40 | 2.00516e+09 | 2.77695e+06 | 0.0671845 | 3.93037 | 4(Loss) | true |
