
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 2019.64 | 1.5591 | 62.688ms | 1313 | 2560 | 239207 | 620 | 0.481541 | 1(Win) | true |
| simdjson (stage-1) | 892.048 | 0.513228 | 143.381ms | 1313 | 4890 | 253794 | 1403.71 | 0.121766 | 2(Loss) | true |
