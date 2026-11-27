
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 7788.38 | 0.102783 | 7253.97ms | 2251027 | 320 | 2.56839e+07 | 275634 | 0.204201 | 1(Win) | true |
| simdjson (stage-1) | 6309.62 | 0.0414756 | 8839.56ms | 2251027 | 1280 | 2.54888e+07 | 340234 | 0.0615081 | 2(Loss) | true |
