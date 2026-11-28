
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 284.01 | 0.139538 | 426.079ms | 1213 | 4890 | 157961 | 4073.12 | 0.0644218 | 1(Win) | true |
| simdjson (reflection) | 274.75 | 0.651798 | 461.37ms | 1213 | 320 | 241003 | 4210.4 | 2.47274 | 2(Loss) | true |
| Glaze | 176.056 | 1.48663 | 713.943ms | 1213 | 30 | 286249 | 6570.67 | 0 | 3(Loss) | true |
