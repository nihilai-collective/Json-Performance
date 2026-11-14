
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 596.17 | 1.05939 | 142.171ms | 905 | 2560 | 602154 | 1447.7 | 0.395284 | 1(Win) | true |
| simdjson (stage-1) | 280.803 | 1.66366 | 344.097ms | 905 | 160 | 418356 | 3073.6 | 2.07226 | 2(Loss) | true |
