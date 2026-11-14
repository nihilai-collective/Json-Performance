
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1594.33 | 0.109599 | 796.46ms | 11812 | 1280 | 76755.8 | 7065.55 | 0.025425 | 1.90052 | 1(Win) | true |
| Jsonifier (two-stage) | 1345.13 | 0.109128 | 935.391ms | 11812 | 4890 | 408416 | 8374.52 | 0.248603 | 2.25361 | 2(Loss) | true |
| Glaze | 1144.48 | 0.0958013 | 1076.51ms | 11812 | 4890 | 434794 | 9842.74 | 0.292211 | 2.64961 | 3(Loss) | true |
| simdjson (ondemand) | 652.32 | 0.0592803 | 1823.9ms | 11812 | 4890 | 512455 | 17268.8 | 0.0476699 | 4.6528 | 4(Loss) | true |
