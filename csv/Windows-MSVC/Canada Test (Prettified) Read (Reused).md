
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1096.49 | 0.749293 | 7751.27ms | 5212421 | 30 | 3.46175e+10 | 4.53352e+06 | 0.898941 | 2.77169 | 1(Win) | true |
| simdjson (ondemand) | 1033.67 | 0.562216 | 8044.87ms | 5212421 | 80 | 5.84811e+10 | 4.80906e+06 | 0.591852 | 2.94011 | 2(Loss) | true |
