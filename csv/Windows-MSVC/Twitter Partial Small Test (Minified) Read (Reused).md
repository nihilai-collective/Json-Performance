
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5931.07 | 0.40742 | 53.3021ms | 2889 | 640 | 2292.42 | 464.531 | 0.0336247 | 0.392496 | 1(Win) | true |
| Jsonifier (two-stage) | 5821.27 | 0.296411 | 51.7485ms | 2889 | 4890 | 9624.05 | 473.292 | 1.41346 | 0.399919 | 2(Loss) | true |
| simdjson (ondemand) | 3275.08 | 0.464079 | 91.4507ms | 2889 | 160 | 2438.68 | 841.25 | 0.447761 | 0.729621 | 3(Loss) | true |
| Glaze | 2879.34 | 0.495736 | 115.144ms | 2889 | 160 | 3600.24 | 956.875 | 0.325521 | 0.830484 | 4(Loss) | true |
