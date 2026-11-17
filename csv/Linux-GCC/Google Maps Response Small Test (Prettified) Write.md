
----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 31984.2 | 0.082293 | 37.5281ms | 11521 | 320 | 25.5732 | 343.522 | 0.0974322 | 0.0717236 | 1(Win) | true |
| Glaze | 5747.31 | 0.0889667 | 195.622ms | 11521 | 80 | 231.417 | 1911.72 | 0.0731787 | 0.42499 | 2(Loss) | true |
| simdjson (reflection) | 584.153 | 0.437565 | 2015.97ms | 11521 | 160 | 1.08376e+06 | 18808.9 | 0.00714371 | 4.23234 | 3(Loss) | true |
