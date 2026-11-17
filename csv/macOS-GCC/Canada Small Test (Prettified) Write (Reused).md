
----
### Canada Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8039.66 | 0.75107 | 188.226ms | 14795 | 1280 | 222395 | 1755 | 0.125513 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 3381.33 | 0.351588 | 413.688ms | 14795 | 1280 | 275507 | 4172.8 | 5.86564 | -(Loss) | false |
| simdjson (reflection) | 243.739 | 0.178139 | 5562.39ms | 14795 | 4890 | 5.20003e+07 | 57888.2 | 0.456217 | 3(Loss) | true |
