
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 1865.79 | 1.54951 | 48.8061ms | 905 | 4890 | 251229 | 462.58 | 0.386276 | 1(Win) | true |
| simdjson (stage-1) | 775.868 | 1.15083 | 116.988ms | 905 | 640 | 104887 | 1112.4 | 0.0359454 | 2(Loss) | true |
