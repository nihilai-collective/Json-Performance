
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6814 | 0.429474 | 6707.38ms | 7351818 | 160 | 3.12449e+09 | 1.02895e+06 | 0.0370614 | 1(Win) | true |
| simdjson (stage-1) | 6017.46 | 0.373194 | 7489.22ms | 7351818 | 40 | 7.56295e+08 | 1.16515e+06 | 1.12111 | 2(Loss) | true |
