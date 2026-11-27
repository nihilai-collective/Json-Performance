
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1257.54 | 0.255456 | 626.426ms | 8051 | 2560 | 622771 | 6105.59 | 0.139916 | 1.95384 | 1(Win) | true |
| Jsonifier (two-stage) | 1112.36 | 0.132125 | 710.663ms | 8051 | 40 | 3326.92 | 6902.5 | 0.156702 | 2.20728 | 2(Loss) | true |
| Glaze | 891.111 | 0.0956067 | 884.773ms | 8051 | 80 | 5428.8 | 8616.25 | 0.274884 | 2.77059 | 3(Loss) | true |
| simdjson (ondemand) | 652.374 | 0.1536 | 1193.14ms | 8051 | 4890 | 1.59808e+06 | 11769.4 | 0.140848 | 3.77971 | 4(Loss) | true |
