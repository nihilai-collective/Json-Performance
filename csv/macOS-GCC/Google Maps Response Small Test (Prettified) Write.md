
----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16862 | 2.91587 | 69.6041ms | 11521 | 640 | 231036 | 651.6 | 4.95916 | 1(Win) | true |
| Glaze | 2833.89 | 0.230815 | 390.728ms | 11521 | 2560 | 205014 | 3877.1 | 0.27522 | 2(Loss) | true |
| simdjson (reflection) | 335.033 | 0.114982 | 3375.57ms | 11521 | 1280 | 1.82e+06 | 32794.6 | 0.0554662 | 3(Loss) | true |
