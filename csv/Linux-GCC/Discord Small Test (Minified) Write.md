
----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11206.4 | 0.429876 | 43.6314ms | 4857 | 30 | 94.7126 | 413.333 | 0.0241994 | 0.206609 | 1(Win) | true |
| simdjson (reflection) | 8258.89 | 0.212944 | 58.6093ms | 4857 | 40 | 57.0538 | 560.85 | 0.0623664 | 0.285964 | 2(Loss) | true |
| Glaze | 3790.81 | 0.308799 | 123.784ms | 4857 | 2560 | 36447 | 1221.9 | 0.125602 | 0.638276 | 3(Loss) | true |
