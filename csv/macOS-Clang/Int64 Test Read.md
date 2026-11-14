
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1703.53 | 0.977809 | 181.527ms | 3862 | 80 | 35754 | 2162.04 | 0.257771 | 1(Win) | true |
| simdjson (stage-1) | 1466.96 | 0.0663063 | 260.561ms | 3862 | 160 | 443.421 | 2510.69 | 0.0117013 | 2(Loss) | true |
