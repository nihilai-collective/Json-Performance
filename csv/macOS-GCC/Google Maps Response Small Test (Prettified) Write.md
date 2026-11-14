
----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 19847 | 2.52839 | 57.611ms | 11521 | 1280 | 250779 | 553.6 | 1.54072 | 1(Win) | true |
| Glaze | 2704.76 | 0.184211 | 409.562ms | 11521 | 2560 | 143349 | 4062.2 | 0.338567 | 2(Loss) | true |
| simdjson (reflection) | 308.389 | 0.610643 | 3552.15ms | 11521 | 320 | 1.51463e+07 | 35628 | 2.51084 | 3(Loss) | true |
