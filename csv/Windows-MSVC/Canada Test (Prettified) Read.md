
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 991.663 | 0.424138 | 7649.73ms | 5212421 | 80 | 3.61622e+10 | 5.01274e+06 | 0.830669 | 3.06472 | 1(Win) | true |
| simdjson (ondemand) | 961.888 | 0.664355 | 7856.1ms | 5212421 | 30 | 3.53633e+10 | 5.16791e+06 | 0.881951 | 3.15969 | 2(Loss) | true |
