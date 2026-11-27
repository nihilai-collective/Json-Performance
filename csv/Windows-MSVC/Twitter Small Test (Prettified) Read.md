
----
### Twitter Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1944.09 | 0.214394 | 192.583ms | 3770 | 160 | 2515.33 | 1849.38 | 0.37037 | 1.55475 | 1(Win) | true |
| simdjson (ondemand) | 1606.86 | 0.243433 | 228.525ms | 3770 | 80 | 2373.42 | 2237.5 | 0.223964 | 1.87661 | 2(Loss) | true |
