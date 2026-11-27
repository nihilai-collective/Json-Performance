
----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16180.1 | 1.81596 | 55.7591ms | 9255 | 2560 | 251213 | 545.5 | 1.96262 | 1(Win) | true |
| Glaze | 2000.15 | 1.14844 | 414.779ms | 9255 | 160 | 410929 | 4412.8 | 1.77122 | 2(Loss) | true |
| simdjson (reflection) | 297.981 | 0.213052 | 2937.88ms | 9255 | 4890 | 1.9474e+07 | 29620.2 | 0.756568 | 3(Loss) | true |
