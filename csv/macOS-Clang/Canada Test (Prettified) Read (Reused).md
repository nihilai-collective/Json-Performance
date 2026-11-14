
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2008.02 | 0.263092 | 9572.33ms | 5373214 | 40 | 1.80305e+09 | 2.55192e+06 | 1.4247 | 1(Win) | true |
| Jsonifier (two-stage) | 1893.43 | 0.149842 | 10051.8ms | 5373214 | 160 | 2.63122e+09 | 2.70635e+06 | 0.056928 | 2(Loss) | true |
| Glaze | 1388.7 | 0.223472 | 6374.27ms | 5373214 | 40 | 2.7199e+09 | 3.68998e+06 | 0.0550377 | 3(Loss) | true |
| simdjson (ondemand) | 1346.85 | 0.288773 | 6549.19ms | 5373214 | 80 | 9.65677e+09 | 3.80464e+06 | 0.243661 | 4(Loss) | true |
