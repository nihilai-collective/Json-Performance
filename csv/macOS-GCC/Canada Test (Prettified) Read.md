
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7828 | 0.45667 | 8237.92ms | 5373214 | 80 | 7.14928e+08 | 654611 | 0.0762009 | 1(Win) | true |
| simdjson (stage-1) | 7155.65 | 0.463674 | 9123.83ms | 5373214 | 80 | 8.82035e+08 | 716118 | 0.240538 | 2(Loss) | true |
