
----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1064.72 | 0.817945 | 460.528ms | 4669 | 640 | 748863 | 4182.03 | 1.92378 | 2.84237 | 1(Win) | true |
| simdjson (ondemand) | 894.716 | 0.249065 | 537.912ms | 4669 | 30 | 4609.2 | 4976.67 | 0.0669344 | 3.38177 | 2(Loss) | true |
