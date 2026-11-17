
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11536.7 | 0.0388888 | 1520.38ms | 183677 | 4890 | 170491 | 15183.5 | 0.0205657 | 0.262772 | 1(Win) | true |
| simdjson (stage-1) | 11244.1 | 0.0760987 | 1559.27ms | 183677 | 640 | 89947.9 | 15578.6 | 0.00100297 | 0.269561 | 2(Loss) | true |
