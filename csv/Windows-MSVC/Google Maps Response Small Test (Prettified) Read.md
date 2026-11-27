
----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1958.44 | 0.191688 | 477.558ms | 9378 | 30 | 2298.85 | 4566.67 | 0.0729395 | 1.25231 | 1(Win) | true |
| Jsonifier (two-stage) | 1885.83 | 0.166912 | 495.871ms | 9378 | 40 | 2506.41 | 4742.5 | 0.193662 | 1.3047 | 2(Loss) | true |
| Glaze | 1357.9 | 0.333085 | 665.229ms | 9378 | 1280 | 616037 | 6586.33 | 0.150871 | 1.81474 | 3(Loss) | true |
| simdjson (ondemand) | 1077.1 | 0.152442 | 845.783ms | 9378 | 4890 | 783472 | 8303.33 | 0.186262 | 2.28625 | 4(Loss) | true |
