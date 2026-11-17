
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 30754.9 | 0.0502586 | 7016.72ms | 2251027 | 4890 | 6.01815e+06 | 69801.8 | 0.0447026 | 0.0804668 | 1(Win) | true |
| simdjson (stage-1) | 20552.8 | 0.129876 | 5358.57ms | 2251027 | 640 | 1.17777e+07 | 104450 | 0.0485919 | 0.120433 | 2(Loss) | true |
