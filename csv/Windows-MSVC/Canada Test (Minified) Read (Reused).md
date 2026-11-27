
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 649.219 | 1.05813 | 6370.05ms | 2251027 | 80 | 9.7937e+10 | 3.30666e+06 | 0.293617 | 3.81312 | 1(Win) | true |
| Jsonifier (two-stage) | 622.639 | 0.834843 | 6524.35ms | 2251027 | 40 | 3.31404e+10 | 3.44782e+06 | 0.767708 | 3.97589 | 2(Loss) | true |
| simdjson (ondemand) | 204.007 | 0.850692 | 8215.04ms | 2251027 | 30 | 2.40401e+11 | 1.05229e+07 | 0.502676 | 12.1354 | 3(Loss) | true |
| Glaze | 183.525 | 0.779328 | 9017.16ms | 2251027 | 40 | 3.32409e+11 | 1.16973e+07 | 0.417587 | 13.49 | 4(Loss) | true |
