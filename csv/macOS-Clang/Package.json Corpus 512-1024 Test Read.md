
----
### Package.json Corpus 512-1024 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20512-1024%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Package.json%20Corpus%20512-1024%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 2931.74 | 0.833717 | 848.11ms | 26071 | 1280 | 6.39898e+06 | 8480.7 | 0.0548051 | 1(Win) | true |
| Jsonifier (generic) | 2854.53 | 0.611173 | 903.977ms | 26071 | 1280 | 3.6273e+06 | 8710.09 | 0.934747 | 2(Loss) | true |
