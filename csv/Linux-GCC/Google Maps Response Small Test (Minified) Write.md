
----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13516.4 | 0.139775 | 34.9936ms | 4390 | 160 | 29.9905 | 309.744 | 0.0705731 | 0.167866 | 1(Win) | true |
| simdjson (reflection) | 11216.2 | 0.225771 | 39.9534ms | 4390 | 30 | 21.3057 | 373.267 | 0 | 0.204905 | 2(Loss) | true |
| Glaze | 3645.82 | 0.174612 | 115.838ms | 4390 | 80 | 321.644 | 1148.34 | 0.118509 | 0.662574 | 3(Loss) | true |
