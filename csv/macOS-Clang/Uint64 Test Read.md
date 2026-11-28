
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1104.67 | 0.252625 | 134.751ms | 1213 | 30 | 209.959 | 1047.2 | 0.136686 | 1(Win) | true |
| Glaze | 586.923 | 0.201724 | 202.993ms | 1213 | 320 | 5058.53 | 1970.97 | 0.150397 | 2(Loss) | true |
| simdjson (ondemand) | 221.726 | 0.393753 | 524.072ms | 1213 | 1280 | 540190 | 5217.28 | 0.398117 | 3(Loss) | true |
