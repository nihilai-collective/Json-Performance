
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1153.19 | 0.317694 | 415.772ms | 4857 | 30 | 4885.06 | 4016.67 | 0.333056 | 2.12375 | 1(Win) | true |
| Jsonifier (two-stage) | 913.609 | 0.342934 | 527.902ms | 4857 | 30 | 9068.97 | 5070 | 0.13132 | 2.69957 | 2(Loss) | true |
| Glaze | 815.683 | 0.280774 | 579.332ms | 4857 | 1280 | 325401 | 5678.67 | 0.501908 | 3.01851 | 3(Loss) | true |
| simdjson (ondemand) | 607.102 | 0.361388 | 770.394ms | 4857 | 640 | 486566 | 7629.69 | 0.0286791 | 4.06171 | 4(Loss) | true |
