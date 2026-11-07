
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1748.09 | 0.95488 | 5994.84ms | 5373214 | 30 | 2.3505e+10 | 2.93137e+06 | 1.40459 | 1.41627 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE DID NOT CONVERGE | 1729.52 | 0.794371 | 5444.43ms | 5373214 | 80 | 4.43154e+10 | 2.96285e+06 | 5.04713 | 1.43143 | -(Tie) | false |
| simdjson (ondemand) | 491.232 | 0.985797 | 8016.79ms | 5373214 | 40 | 4.22991e+11 | 1.04315e+07 | 0.473979 | 5.04002 | 3(Loss) | true |
| Glaze | 465.889 | 0.915111 | 8195.98ms | 5373214 | 40 | 4.05239e+11 | 1.0999e+07 | 0.175503 | 5.31416 | 4(Loss) | true |
