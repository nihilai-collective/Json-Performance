
----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11496.7 | 1.76771 | 42.8022ms | 4857 | 4890 | 248040 | 402.899 | 0.373437 | 1(Win) | true |
| simdjson (reflection) | 9257.96 | 1.48895 | 52.7631ms | 4857 | 4890 | 271378 | 500.326 | 1.15761 | 2(Loss) | true |
| Glaze | 2735.88 | 0.425318 | 173.633ms | 4857 | 4890 | 253558 | 1693.06 | 1.16248 | 3(Loss) | true |
