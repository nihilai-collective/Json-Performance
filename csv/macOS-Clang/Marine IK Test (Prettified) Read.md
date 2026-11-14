
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7445.05 | 0.234979 | 5997.38ms | 7351818 | 160 | 7.83489e+08 | 941732 | 0.174359 | 1(Win) | true |
| simdjson (stage-1) | 6011.39 | 0.120224 | 7498.68ms | 7351818 | 160 | 3.14589e+08 | 1.16633e+06 | 0.0905529 | 2(Loss) | true |
