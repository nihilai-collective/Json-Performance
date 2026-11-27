
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 2158.31 | 1.33908 | 56.3389ms | 1213 | 4890 | 251891 | 535.977 | 0.0330527 | 1(Win) | true |
| simdjson (stage-1) | 829.678 | 0.510869 | 142.071ms | 1213 | 4890 | 248102 | 1394.28 | 0.0656648 | 2(Loss) | true |
