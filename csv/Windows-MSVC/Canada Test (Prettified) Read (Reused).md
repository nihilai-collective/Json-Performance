
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 509.756 | 0.955329 | 7242.42ms | 5212421 | 40 | 3.47153e+11 | 9.75163e+06 | 1.44661 | 4.85688 | 1(Win) | true |
| simdjson (ondemand) | 480.049 | 1.19089 | 7816.76ms | 5212421 | 40 | 6.08289e+11 | 1.03551e+07 | 2.28169 | 5.15742 | 2(Loss) | true |
