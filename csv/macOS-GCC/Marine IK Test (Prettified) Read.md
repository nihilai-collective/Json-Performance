
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7192.77 | 0.548131 | 7178.02ms | 7351818 | 30 | 8.56421e+08 | 974763 | 0.841153 | 1(Win) | true |
| simdjson (stage-1) | 5692.75 | 0.811724 | 7240.92ms | 7351818 | 80 | 7.99564e+09 | 1.23161e+06 | 1.37118 | 2(Loss) | true |
