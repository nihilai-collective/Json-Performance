
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 5684.42 | 0.297434 | 53.4536ms | 2889 | 640 | 1330.11 | 484.688 | 0.385356 | 0.411558 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 5682.58 | 0.292586 | 52.3551ms | 2889 | 640 | 1287.93 | 484.844 | 0.616083 | 0.411154 | 1(Tie) | true |
| simdjson (ondemand) | 3976.02 | 0.450353 | 73.401ms | 2889 | 4890 | 47622.5 | 692.945 | 0.019094 | 0.598959 | 3(Loss) | true |
| Glaze | 2861.25 | 0.358304 | 100.326ms | 2889 | 4890 | 58209.9 | 962.924 | 0.105916 | 0.839967 | 4(Loss) | true |
