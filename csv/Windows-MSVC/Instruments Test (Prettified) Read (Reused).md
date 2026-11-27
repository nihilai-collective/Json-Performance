
----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2275.92 | 0.0848054 | 8096.52ms | 183677 | 2560 | 1.09064e+07 | 76965.7 | 0.786364 | 1.08741 | 1(Win) | true |
| Jsonifier (two-stage) | 2068.83 | 0.211337 | 9136.2ms | 183677 | 320 | 1.02461e+07 | 84670 | 0.056806 | 1.1963 | 2(Loss) | true |
| Glaze | 1575.69 | 0.118779 | 5926.59ms | 183677 | 1280 | 2.23181e+07 | 111169 | 0.315245 | 1.57088 | 3(Loss) | true |
| simdjson (ondemand) | 1544.07 | 0.148678 | 6013.84ms | 183677 | 640 | 1.82075e+07 | 113446 | 0.15965 | 1.60303 | 4(Loss) | true |
