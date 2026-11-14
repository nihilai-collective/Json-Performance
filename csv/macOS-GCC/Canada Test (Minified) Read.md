
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5863.33 | 0.979483 | 10690.3ms | 2251027 | 30 | 3.85824e+08 | 366131 | 0.100119 | 1(Win) | true |
| simdjson (stage-1) | 5006.73 | 0.308785 | 5408.09ms | 2251027 | 640 | 1.12187e+09 | 428772 | 0.390843 | 2(Loss) | true |
