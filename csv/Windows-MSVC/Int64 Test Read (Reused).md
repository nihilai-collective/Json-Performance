
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 916.192 | 0.159331 | 434.933ms | 3862 | 40 | 1641.03 | 4020 | 0.0829876 | 3.29297 | 1(Win) | true |
| simdjson (ondemand) | 622.494 | 0.116965 | 635.35ms | 3862 | 30 | 1436.78 | 5916.67 | 0.737798 | 4.86063 | 2(Loss) | true |
