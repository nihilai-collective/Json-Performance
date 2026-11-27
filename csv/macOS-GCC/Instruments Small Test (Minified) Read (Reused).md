
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1334.07 | 0.226855 | 352.602ms | 4669 | 4890 | 280348 | 3337.69 | 0.045368 | 1(Win) | true |
| simdjson (ondemand) | 1176.07 | 0.272543 | 396.04ms | 4669 | 2560 | 272580 | 3786.1 | 0.663798 | 2(Loss) | true |
