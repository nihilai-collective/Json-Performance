
----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7844.91 | 0.187088 | 148.736ms | 11812 | 320 | 2309.46 | 1435.94 | 0.0652458 | 0.309509 | 1(Win) | true |
| Glaze | 3175.42 | 0.225409 | 375.874ms | 11812 | 40 | 2557.69 | 3547.5 | 0.0234962 | 0.774255 | 2(Loss) | true |
