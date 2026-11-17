
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 10130.6 | 0.566574 | 103.998ms | 9578 | 4890 | 127615 | 901.654 | 0.384546 | 1(Win) | true |
| Jsonifier | 9040.27 | 1.11048 | 113.254ms | 9578 | 320 | 40286.5 | 1010.4 | 0.394322 | 2(Loss) | true |
| Glaze | 4600.27 | 1.07478 | 213.189ms | 9578 | 640 | 291474 | 1985.6 | 2.39274 | 3(Loss) | true |
