
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8792.51 | 0.262586 | 7820.77ms | 5373214 | 40 | 9.36799e+07 | 582802 | 1.26251 | 1(Win) | true |
| simdjson (stage-1) | 7633.42 | 0.155478 | 8609.85ms | 5373214 | 80 | 8.71477e+07 | 671297 | 0.707279 | 2(Loss) | true |
