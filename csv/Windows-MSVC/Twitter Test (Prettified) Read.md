
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 18857.9 | 0.292532 | 3198.72ms | 631514 | 1280 | 1.11722e+07 | 31936.7 | 0.314573 | 0.13117 | 1(Win) | true |
| simdjson (stage-1) | 17307.8 | 0.17169 | 3525.14ms | 631514 | 2560 | 9.13725e+06 | 34797 | 0.602733 | 0.142913 | 2(Loss) | true |
