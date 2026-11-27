
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1535.83 | 0.56231 | 5873.35ms | 5373214 | 80 | 2.81596e+10 | 3.33651e+06 | 2.68102 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1528.18 | 0.38497 | 6086.87ms | 5373214 | 80 | 1.33309e+10 | 3.35319e+06 | 0.234876 | 1(Tie) | true |
| Glaze | 1467.58 | 0.125216 | 6179.09ms | 5373214 | 30 | 5.73469e+08 | 3.49167e+06 | 0.41932 | 3(Loss) | true |
| Jsonifier (two-stage) | 1317.86 | 0.51948 | 6787.66ms | 5373214 | 80 | 3.26408e+10 | 3.88836e+06 | 1.55791 | 4(Loss) | true |
| simdjson (ondemand) | 1210.52 | 1.06765 | 7132.7ms | 5373214 | 30 | 6.12779e+10 | 4.23315e+06 | 3.22554 | 5(Loss) | true |
