
----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3609.09 | 0.0794443 | 250.358ms | 9378 | 30 | 116.271 | 2478.07 | 0.0927282 | 0.678769 | 1(Win) | true |
| Jsonifier (two-stage) | 3329.32 | 0.0850888 | 272.178ms | 9378 | 40 | 208.985 | 2686.3 | 0.0892625 | 0.736282 | 2(Loss) | true |
| Glaze | 2487.85 | 0.0879533 | 357.041ms | 9378 | 40 | 399.887 | 3594.9 | 0.0881654 | 0.987948 | 3(Loss) | true |
| simdjson (ondemand) | 2140.22 | 0.123544 | 421.282ms | 9378 | 40 | 1066.11 | 4178.8 | 0.105979 | 1.14944 | 4(Loss) | true |
